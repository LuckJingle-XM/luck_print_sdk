# luck_print_sdk

[Introduction in English](./README.md)
[中文](./README_CN.md)
[한국어](./README_KR.md)

## 소개
이 라이브러리는 iOS 플랫폼에서 프린터와 통신하기 위한 것입니다. 이를 필요로 하는 사용자들은 아래 튜토리얼을 참조하여 SDK를 통합하고 LuckJingle 프린터와 상호 작용을 구현할 수 있습니다!

## 준비 단계
asKey를 얻기 위해 관련 인원에게 문의하여 SDK를 정상적으로 사용할 수 있도록하십시오. asKey를 신청하기 전에 지원하는 프린터 모델을 확인하십시오.

## 설치

#### 직접 가져오기
이 라이브러리에서 파일인 LuckBleSDK.framework, ImageDataProcesser.framework을 다운로드하고 프로젝트에 가져옵니다.


#### cocoapods
Cocoapods를 사용하여 종속성 관리
```
pod 'printer_framework_ios'
```

## 사용 지침

#### asKey 설정

불가피한 상황으로 인해 국내 사용을 위한 두 가지 환경이 있습니다. 응용 프로그램이로드 된 후에 설정하십시오.
```swift
// 국내 사용자
JKBleManager.sharedInstance().asKey = "your askey"
// 국외 사용자
JKBleManager.sharedInstance().abroadAsKey = "your askey"
```

#### 블루투스 이벤트 모니터링

```swift
// 디바이스 연결 성공 이벤트
#define kBleDidConnectPeripheralNoticeName @"kBleDidConnectPeripheralNoticeName"
// 연결 해제 이벤트
#define kBleDidDisconnectPeripheralNoticeName @"kBleDidDisconnectPeripheralNoticeName"
// 연결 실패 이벤트
#define kBleDidFailToConnectPeripheralNoticeName @"kBleDidFailToConnectPeripheralNoticeName"
// 블루투스 상태 변경 이벤트
#define kBleDidChangeStateNoticeName @"kBleDidChangeStateNoticeName"
// 디바이스 발견 이벤트
#define kBleDidPeripheralFoundNoticeName @"kBleDidPeripheralFoundNoticeName"
// 장치를 지원하지 않아 장치가 연결이 끊김
#define kLuckPrinterDidNotSupportNoticeName @"kLuckPrinterDidNotSupportNoticeName"

```

#### 디바이스 연결

```swift
override func viewDidLoad() {
    super.viewDidLoad()

    // 디바이스 발견 이벤트를 듣습니다
    NotificationCenter.default.addObserver(self, selector: #selector(luckBleDidDiscoverPrinters(sender:)), name: NSNotification.Name.init("kBleDidPeripheralFoundNoticeName"), object: nil)
    // 디바이스 연결 이벤트를 듣습니다
    NotificationCenter.default.addObserver(self, selector: #selector(luckBleDidConnect(sender:)), name: NSNotification.Name.init("kBleDidConnectPeripheralNoticeName"), object: nil)
    
}

@objc func luckBleDidDiscoverPrinters(sender: Notification) {
    // 새로운 장치를 발견하면 필요에 따라 필터링하여 장치가 비활성화되어 사용자 경험이 영향을받지 않도록하십시오.
    guard let obj = sender.object as? NSDictionary else { return }
    guard let peripheral = obj["peripheral"] as? CBPeripheral else { return }
    if device_list.contains(peripheral) {
        return
    }
    device_list.append(peripheral)
    tableView.reloadData()
}

// 디바이스 연결
override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
    tableView.deselectRow(at: indexPath, animated: true)
    
    let peripheral = self.device_list[indexPath.row];
    JKBleManager.sharedInstance().connect(peripheral, timeout: 5)
}


@objc func luckBleDidConnect(sender: Notification) {
    // 연결 성공 연결이 성공하면 JKBleManager.sharedInstance().printer에만 값이 있습니다
    self.navigationController?.popViewController(animated: true)
}

```


#### 디바이스 정보 가져 오기
```swift
printer.getInfo { [weak self] info, error in
    guard let weakself = self else { return }
    // 다른 모델에서 가져온 정보는 일부 필드가 비어 있을 수 있습니다.
    let str = """
        state = \(info.state) thick = \(info.thick) time = \(info.closeTime)
        power = \(info.power) speed = \(info.speed) paper = \(info.paperType)
        sn = \(info.sn)model = \(info.model) version = \(info.version)
        """
}

// 농도 설정
printer.thick = 1
// 종이 종류 설정
printer.paperType = .ZD
// 종료 시간 설정
printer.closeTime = 20
// 프린터 속성을 설정 한 후에는 프린터에 동기화하려면 호출하십시오.
printer.synchronize {
                    
}

```


#### 예시 인쇄

```swift
guard let printer = JKBleManager.sharedInstance().printer else { return }
// 농도 설정, 기본값은 1이며 중간 정도입니다. 필요하지 않은 경우 무시하십시오.
printer.thick = 1
// 종이 종류 설정, A4 장치 만 필요합니다. 미니 무시하십시오.
printer.paperType = .ZD
// 종이 크기 설정, 데이터 형식은 sdk를 참조하십시오. 장치에서 한 가지 크기 만 지원하므로 무시하십시오.
printer.labelSize = size
// 라벨 인쇄 여부
printer.isLabel = true
// 프린터에 필요한 크기로 축소
let printImage = printer.normalPreviewImage(zx)


// 아래 두 메서드는 필요에 따라 호출하십시오.

// 연속 용지 인쇄 호출,
printer.print([printImage], copies: 1) {error in
    print("인쇄 완료")
}

// 라벨 인쇄 호출
printer.printLabel([printImage], copies: 1) {error in
    print("인쇄 완료")
}

```

#### 기타
더 많은 사용 사례는이 라이브러리를 다운로드하고 Example을 참조하십시오.

