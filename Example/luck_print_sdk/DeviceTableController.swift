//
//  DeviceTableController.swift
//  LuckPrinterSDK
//
//  Created by junky on 2023/9/13.
//

import UIKit
import LuckBleSDK

class DeviceTableController: UITableViewController {

    var device_list: [CBPeripheral] = []
    var didConnectDevice: ((String) -> (Void))?
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Listen for device discovery events.
        NotificationCenter.default.addObserver(self, selector: #selector(luckBleDidDiscoverPrinters(sender:)), name: NSNotification.Name.init("kBleDidPeripheralFoundNoticeName"), object: nil)
        // Listen for device connection events
        NotificationCenter.default.addObserver(self, selector: #selector(luckBleDidConnect(sender:)), name: NSNotification.Name.init("kBleDidConnectPeripheralNoticeName"), object: nil)
        
    }

    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        // End the scanning
        JKBleManager.sharedInstance().stopScanPrinters()
    }
    
    // MARK: - Notice
    
    // Note: Please filter out devices that are not needed to avoid disrupting the user experience due to disabled devices.
    @objc func luckBleDidDiscoverPrinters(sender: Notification) {
        
        guard let obj = sender.object as? NSDictionary else { return }
        guard let peripheral = obj["peripheral"] as? CBPeripheral else { return }
        if device_list.contains(peripheral) {
            return
        }
        device_list.append(peripheral)
        tableView.reloadData()
    }
    
    @objc func luckBleDidConnect(sender: Notification) {
        
        self.navigationController?.popViewController(animated: true)
    }
    
    
    
    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        // #warning Incomplete implementation, return the number of sections
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete implementation, return the number of rows
        return device_list.count
    }

    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "device_cell", for: indexPath)

        cell.textLabel?.text = device_list[indexPath.row].name
        return cell
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        let peripheral = self.device_list[indexPath.row];
        // connect to printer
        JKBleManager.sharedInstance().connect(peripheral, timeout: 5)
        if let callback = didConnectDevice,
           let name = peripheral.name
        {
            callback(name)
        }
    }
    
    
    // Start scanning.
    @IBAction func startScan(_ sender: UIBarButtonItem) {
        JKBleManager.sharedInstance().scanPrinters()
    }

    deinit{
        print("\(type(of: self)) deinit")
    }
    

}
