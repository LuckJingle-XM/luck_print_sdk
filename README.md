# luck_print_sdk

[Introduction in English](./README.md)
[中文](./README_CN.md)
[한국어](./README_KR.md)

## Introduction
This library is used for communication with printers on the iOS platform. For those who need it, please refer to the tutorial below to integrate the SDK and interact with LuckJingle printers!




## Preparation
Please contact the relevant personnel to obtain the asKey to ensure that you can use the SDK normally. Before applying for the asKey, please confirm the supported printer models.

## Installation

#### Direct import
Please download the files from this library: LuckBleSDK.framework, ImageDataProcesser.framework, and import them into your project.


#### cocoapods
Use Cocoapods for dependency management.
```
# Not supported yet
pod 'printer_framework_ios'
```

## Instructions

#### Set asKey

Due to uncontrollable factors, we have two environments, one for domestic use and one for overseas use. Please set it after the application is loaded.
```swift
// For domestic users
JKBleManager.sharedInstance().asKey = "your askey"
// For overseas users
JKBleManager.sharedInstance().abroadAsKey = "your askey"
```

#### Bluetooth Event Monitoring

```swift
// Connected device success event
#define kBleDidConnectPeripheralNoticeName @"kBleDidConnectPeripheralNoticeName"
// Disconnection event
#define kBleDidDisconnectPeripheralNoticeName @"kBleDidDisconnectPeripheralNoticeName"
// Connection failure event
#define kBleDidFailToConnectPeripheralNoticeName @"kBleDidFailToConnectPeripheralNoticeName"
// Bluetooth status change event
#define kBleDidChangeStateNoticeName @"kBleDidChangeStateNoticeName"
// Found device event
#define kBleDidPeripheralFoundNoticeName @"kBleDidPeripheralFoundNoticeName"
// Not supporting the device, the device will be disconnected
#define kLuckPrinterDidNotSupportNoticeName @"kLuckPrinterDidNotSupportNoticeName"
```

#### Connect Device

```swift
override func viewDidLoad() {
    super.viewDidLoad()

    // Listen for device discovery events
    NotificationCenter.default.addObserver(self, selector: #selector(luckBleDidDiscoverPrinters(sender:)), name: NSNotification.Name.init("kBleDidPeripheralFoundNoticeName"), object: nil)
    // Listen for device connection events
    NotificationCenter.default.addObserver(self, selector: #selector(luckBleDidConnect(sender:)), name: NSNotification.Name.init("kBleDidConnectPeripheralNoticeName"), object: nil)
    
}

@objc func luckBleDidDiscoverPrinters(sender: Notification) {
    // Discover new devices, please filter according to your needs to avoid affecting the user experience due to disabled devices
    guard let obj = sender.object as? NSDictionary else { return }
    guard let peripheral = obj["peripheral"] as? CBPeripheral else { return }
    if device_list.contains(peripheral) {
        return
    }
    device_list.append(peripheral)
    tableView.reloadData()
}

// Connect device
override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
    tableView.deselectRow(at: indexPath, animated: true)
    
    let peripheral = self.device_list[indexPath.row];
    JKBleManager.sharedInstance().connect(peripheral, timeout: 5)
}


@objc func luckBleDidConnect(sender: Notification) {
    // Connection successful Only when connected successfully will JKBleManager.sharedInstance().printer have a value
    self.navigationController?.popViewController(animated: true)
}
```


#### Get Device Information
```swift
printer.getInfo { [weak self] info, error in
    guard let weakself = self else { return }
    // Some fields of information may be empty for different models
    let str = """
        state = \(info.state) thick = \(info.thick) time = \(info.closeTime)
        power = \(info.power) speed = \(info.speed) paper = \(info.paperType)
        sn = \(info.sn)model = \(info.model) version = \(info.version)
        """
}

// Set density
printer.thick = 1
// Set paper type
printer.paperType = .ZD
// Set shutdown time
printer.closeTime = 20
// After setting the printer attributes, please call synchronize to sync to the printer
printer.synchronize {
                    
}
```


#### Printing Example

```swift
guard let printer = JKBleManager.sharedInstance().printer else { return }
// Set density, default is 1, moderate. If not needed, ignore it
printer.thick = 1
// Set paper type, only needed for A4 devices, ignore it for mini devices
printer.paperType = .ZD
// Set paper size, refer to the SDK for data types, ignore it if the device only supports one size
printer.labelSize = size
// Is it label printing
printer.isLabel = true
// Scale to the size required by the printer
let printImage = printer.normalPreviewImage(zx)


// Call the following two methods as needed

// Call continuous paper printing,
printer.print([printImage], copies: 1) {error in
    print("Printing completed")
}

// Call label printing
printer.printLabel([printImage], copies: 1) {error in
    print("Printing completed")
}
```

#### Others
For more usage scenarios, please refer to the downloaded library and the Example folder.

