//
//  ImageController.swift
//  LuckPrinterSDK
//
//  Created by junky on 2023/9/18.
//

import UIKit

class ImageController: UIViewController {

    var image: UIImage?
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        guard let image = image else { return }
        imageView.image = image;
        
        self.title = "\(image.size.width)*\(image.size.height)"
        
    }
    
    override class func awakeFromNib() {
        super.awakeFromNib()
        
    }
    
    
    @IBOutlet weak var imageView: UIImageView!
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
