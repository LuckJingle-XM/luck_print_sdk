//
//  ActionTableController.swift
//  LuckPrinterSDK
//
//  Created by junky on 2023/9/13.
//

import UIKit
import LuckBleSDK

class ActionTableController: UITableViewController {
    
    
    
    var image: UIImage?

    var action_list: [[String]] = [
        ["device info"],
        ["Print concentration", "Close time", "Speed", "Sync information to the printer"],
        ["Update firmware", "Print image", "Print label"]
    ]
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        NotificationCenter.default.addObserver(self, selector: #selector(luckBleDidDisconnect(sender:)), name: NSNotification.Name.init("kBleDidDisconnectPeripheralNoticeName"), object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(luckBleDidConnect(sender:)), name: NSNotification.Name.init("kBleDidConnectPeripheralNoticeName"), object: nil)
        
    }
    
    @objc func luckBleDidDisconnect(sender: NSNotification) {
        self.title = "Luck Printer"
    }
    
    @objc func luckBleDidConnect(sender: NSNotification) {
        guard let dic = sender.object as? [String: CBPeripheral] else { return }
        guard let per = dic["peripheral"] else { return }
        self.title = per.name
    }

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        // #warning Incomplete implementation, return the number of sections
        return action_list.count
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete implementation, return the number of rows
        let list = action_list[section]
        return list.count
    }
    
    override func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        let titles = ["read properties", "waybill", "write properties", "action"]
        return titles[section]
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "action_cell", for: indexPath)
        let list = action_list[indexPath.section]
        cell.textLabel?.text = list[indexPath.row];

        return cell
    }
    

    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        guard let printer = JKBleManager.sharedInstance().printer else { return }
        
        if indexPath.section == 0 {
            
            if (indexPath.row == 0) {
//                printer.sendTask(LPSendTask.timeout())
                printer.getInfo { [weak self] info, error in
                    guard let weakself = self else { return }
                    let str = """
                        state = \(info.state) thick = \(info.thick) time = \(info.closeTime)
                        power = \(info.power) speed = \(info.speed) paper = \(info.paperType)
                        sn = \(info.sn)model = \(info.model) version = \(info.version)
                        """
                    print(str)
                }
            }
        }else if indexPath.section == 1 {
            if (indexPath.row == 0) {
                showSheet(["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"], title: "Print concentration") { value in
                    guard let time = UInt(value) else { return }
                    printer.thick = time
                }
            }else if (indexPath.row == 1) {
                showSheet(["10", "20", "30"], title: "Close time") { value in
                    guard let time = UInt(value) else { return }
                    printer.closeTime = time
                }
            }else if (indexPath.row == 2) {
                
                showSheet(["roll" , "fold "], title: "Paper type") { value in
                    if (value == "roll") {
                        printer.paperType = .JZ
                    }else {
                        printer.paperType = .ZD
                    }
                }
            }else {
                printer.synchronize {
                    
                }
            }
        }else {
            if (indexPath.row == 0) {
                guard let path = Bundle.main.path(forResource: "B58K_BR8551_v1.13.bin", ofType: nil) else { return }
                guard let data = NSData.init(contentsOfFile: path) as? Data else { return }
                printer.updateVersion(data) {error in
                    print("compelete")
                }
            }else if (indexPath.row == 1) {
                guard let selectedVC = UIStoryboard(name: "Main", bundle: nil).instantiateViewController(withIdentifier: "selected_image_VC") as? SelectedImageController else { return }
                selectedVC.isLabel = false
                self.navigationController?.pushViewController(selectedVC, animated: true)
            }else if (indexPath.row == 2) {
                guard let selectedVC = UIStoryboard(name: "Main", bundle: nil).instantiateViewController(withIdentifier: "selected_image_VC") as? SelectedImageController else { return }
                selectedVC.isLabel = true
                self.navigationController?.pushViewController(selectedVC, animated: true)
            }
        }
        
    }
    
    
    
    
    
    @IBAction func disconnect(_ sender: UIBarButtonItem) {
        guard let peripheral = JKBleManager.sharedInstance().printer?.peripheral else { return }
        JKBleManager.sharedInstance().disconnect(peripheral)
    }
    
    
}



extension ActionTableController {
    
    
    func showSheet(_ list: [Any], title: String? = nil, compelete: ((String)->Void)? = nil) {
        
        let sheet = UIAlertController(title: title, message: nil, preferredStyle: .actionSheet)
        for str in list {
            let action = UIAlertAction(title: "\(str)", style: UIAlertAction.Style.default) { act in
                if let callback = compelete,
                   let tit = act.title {
                    callback(tit)
                }
            }
            sheet.addAction(action)
        }
        let action = UIAlertAction(title: "cancel", style: UIAlertAction.Style.cancel)
        sheet.addAction(action)
        self.present(sheet, animated: true)
    }
    
    
}


