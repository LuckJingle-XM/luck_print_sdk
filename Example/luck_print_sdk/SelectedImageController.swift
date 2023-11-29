//
//  SelectedImageController.swift
//  LuckPrinterSDK
//
//  Created by junky on 2023/9/23.
//

import UIKit
import LuckBleSDK

class SelectedImageController: UITableViewController {

    var isLabel: Bool = false
    var images: [String] = ["Binary algorithm", "Dithering algorithm"];
    var selectedIndex: Int = 0
    
    var previewImage: UIImage?
    
    
    lazy var imagePicker: UIImagePickerController = {
        let tmp = UIImagePickerController()
        tmp.delegate = self
        tmp.sourceType = .photoLibrary
        return tmp
    }()
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        tableView.reloadData()
        JKBleManager.sharedInstance().printer?.isLabel = isLabel
    }

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        // #warning Incomplete implementation, return the number of sections
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete implementation, return the number of rows
        return images.count
    }

    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "selected_cell", for: indexPath)
        cell.textLabel?.text = images[indexPath.row]
        return cell
    }
    
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        tableView.deselectRow(at: indexPath, animated: true)
        selectedIndex = indexPath.row
        present(imagePicker, animated: true)
        
    }

    func setPaperType() {
        guard let printer = JKBleManager.sharedInstance().printer else { return }
        showSheet(["roll", "fold"], title: "Paper type") { [weak self] value in
            guard let weakself = self else { return }
            
            if (value == "roll") {
                printer.paperType = .JZ
            }else {
                printer.paperType = .ZD
            }
            
            weakself.setPaperSize()
        }
    }
    
    func setPaperSize() {
        guard let printer = JKBleManager.sharedInstance().printer else { return }
        var list: [String] = printer.supportWidthFormm
        if isLabel {
            list = printer.supportLabelSizes.map({ size in
                return size.labelTitle
            })
        }
        showSheet(list, title: "paper size") { [weak self] value in
            
            guard let weakself = self else { return }
            
            for size in printer.supportLabelSizes {
                
                if weakself.isLabel {
                    if size.labelTitle == value {
                        printer.labelSize = size
                        break
                    }
                }else {
                    if size.widthTitle == value {
                        printer.labelSize = size
                        break
                    }
                }
                
            }
            if let weakself = self {
                weakself.setCopies()
            }
        }
        
    }
    
    
    func setCopies() {
        guard let printer = JKBleManager.sharedInstance().printer else { return }
        showSheet(["1", "2", "3", "4", "5"], title: "copies") { [weak self] value in
            
            if let weakself = self,
               let previewImage = weakself.previewImage,
               let copies = Int32(value) {
                
                let printImg = weakself.selectedIndex == 0 ? printer.ezPreviewImage(previewImage) : printer.ddPreviewImage(previewImage)
                if weakself.isLabel {
                    printer.printLabel([printImg], copies: UInt(copies)) {error in
                        print("compelete")
                    }
                }else {
                    printer.print([printImg], copies: UInt(copies)) {error in
                        print("compelete")
                    }
                }
                
            }
            
        }
    }

}

extension SelectedImageController {
    
    
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


extension SelectedImageController: UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    
    
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [String : Any]) {
        
        picker.dismiss(animated: true)
        guard let image = info[UIImagePickerControllerOriginalImage] as? UIImage else { return }
        guard let printer = JKBleManager.sharedInstance().printer else { return }
        self.previewImage = image
        
        if printer.isMDModel {
            printer.mdWidth = 75;
            printer.mdHeight = 130;
            printer.mdM = 2;
            setCopies()
            return
        }
        
        if isLabel {
            setPaperSize()
        }else {
            setPaperType()
        }
    }
    
}
