# luck_print_sdk

[Introduction in English](../README.md)
[中文](../README_CN.md)

## Introduction
本库用于在iOS平台上与打印机通讯用的 凡有需求者，可参照以下教程接入sdk，实现与LuckJingle打印机交互！

## 准备阶段
请联系相关人员获取asKey，以确保您能正常使用sdk，申请askey前请确认要支持的打印机型号

## 安装

#### 直接导入
请下载本库中的文件：LuckBleSDK.framework，ImageDataProcesser.framework，并引入
项目中


#### cocoapods
利用cocoapods依赖管理
```
pod 'printer_framework_ios'
```

## 使用说明

#### 设置askey

因不可抗力，我们有两套环境，一套国内使用，一套国外使用，请在应用加载后设置
```swift
// 国内用户
JKBleManager.sharedInstance().asKey = "your askey"
// 国外用户
JKBleManager.sharedInstance().abroadAsKey = "your askey"
```

#### 蓝牙事件监听

```swift
// 连接设备成功事件
#define kBleDidConnectPeripheralNoticeName @"kBleDidConnectPeripheralNoticeName"
// 断开连接事件
#define kBleDidDisconnectPeripheralNoticeName @"kBleDidDisconnectPeripheralNoticeName"
// 连接失败事件
#define kBleDidFailToConnectPeripheralNoticeName @"kBleDidFailToConnectPeripheralNoticeName"
// 蓝牙状态改变事件
#define kBleDidChangeStateNoticeName @"kBleDidChangeStateNoticeName"
// 发现设备事件
#define kBleDidPeripheralFoundNoticeName @"kBleDidPeripheralFoundNoticeName"
// 不支持设备，设备会被断开
#define kLuckPrinterDidNotSupportNoticeName @"kLuckPrinterDidNotSupportNoticeName"
```

#### 连接设备

```swift
override func viewDidLoad() {
    super.viewDidLoad()

    // 监听发现设备事件
    NotificationCenter.default.addObserver(self, selector: #selector(luckBleDidDiscoverPrinters(sender:)), name: NSNotification.Name.init("kBleDidPeripheralFoundNoticeName"), object: nil)
    // 监听设备连接事件
    NotificationCenter.default.addObserver(self, selector: #selector(luckBleDidConnect(sender:)), name: NSNotification.Name.init("kBleDidConnectPeripheralNoticeName"), object: nil)
    
}

@objc func luckBleDidDiscoverPrinters(sender: Notification) {
    // 发现新设备，请按自己需求做过滤，避免因设备被禁用影响用户体验
    guard let obj = sender.object as? NSDictionary else { return }
    guard let peripheral = obj["peripheral"] as? CBPeripheral else { return }
    if device_list.contains(peripheral) {
        return
    }
    device_list.append(peripheral)
    tableView.reloadData()
}

// 连接设备
override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
    tableView.deselectRow(at: indexPath, animated: true)
    
    let peripheral = self.device_list[indexPath.row];
    JKBleManager.sharedInstance().connect(peripheral, timeout: 5)
}


@objc func luckBleDidConnect(sender: Notification) {
    // 连接成功 只有连接成功JKBleManager.sharedInstance().printer才会有值
    self.navigationController?.popViewController(animated: true)
}
```


#### 获取设备信息
```swift
printer.getInfo { [weak self] info, error in
    guard let weakself = self else { return }
    // 不同型号获取到的信息有些字段可能为空
    let str = """
        state = \(info.state) thick = \(info.thick) time = \(info.closeTime)
        power = \(info.power) speed = \(info.speed) paper = \(info.paperType)
        sn = \(info.sn)model = \(info.model) version = \(info.version)
        """
}

// 设置浓度
printer.thick = 1
// 设置纸张类型
printer.paperType = .ZD
// 设置关机时间
printer.closeTime = 20
// 设置打印机属性后，请调用同步到打印机
printer.synchronize {
                    
}
```


#### 打印示例

```swift
guard let printer = JKBleManager.sharedInstance().printer else { return }
// 设置浓度，默认1，适中，如果不需要请忽略
printer.thick = 1
// 设置纸张类型，A4设备才需要，迷你请忽略
printer.paperType = .ZD
// 设置纸张尺寸，数据类型请参考sdk，设备只支持一种尺寸的忽略
printer.labelSize = size
// 是否是标签打印
printer.isLabel = true
// 缩放到打印机需要的尺寸
let printImage = printer.normalPreviewImage(zx)


// 下面两个方法按需调用

// 调用连续纸打印,
printer.print([printImage], copies: 1) {error in
    print("打印完成")
}

// 调用标签打印
printer.printLabel([printImage], copies: 1) {error in
    print("打印完成")
}
```

#### 其他
更多使用情况请参考下载本库，参考Example

