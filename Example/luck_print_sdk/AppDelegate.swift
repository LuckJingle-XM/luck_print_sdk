//
//  AppDelegate.swift
//  luck_print_sdk
//
//  Created by 汤俊杰 on 11/29/2023.
//  Copyright (c) 2023 汤俊杰. All rights reserved.
//

import UIKit
import LuckBleSDK

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?


    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        
        // Please contact the relevant personnel to register the key.
        JKBleManager.sharedInstance().asKey = "your askey"
        // Listen for Bluetooth state change events.
        NotificationCenter.default.addObserver(self, selector: #selector(bleDidChangeState(sender:)), name: NSNotification.Name.init("kBleDidChangeStateNoticeName"), object: nil)
        return true
    }
    
    
    @objc func bleDidChangeState(sender: Notification) {
        guard let dic = sender.object as? [String: Any] else { return }
        guard let enable = dic["state"] as? Int64 else { return }
        if (enable == CBManagerState.poweredOn.rawValue) {
            // Automatically connect to the device if a previously connected device is available.
            JKBleManager.sharedInstance().autoConnectToLastPrinterIfHas()
        }
    }
    

}

