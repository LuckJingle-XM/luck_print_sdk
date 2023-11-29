//
//  LuckPrinter.h
//  LuckBleSDK
//
//  Created by junky on 2023/9/18.
//


#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <LuckBleSDK/LuckPrinterInfo.h>
#import <LuckBleSDK/LPSendTask.h>


#define kLuckPrinterDidNotSupportNoticeName @"kLuckPrinterDidNotSupportNoticeName"


NS_ASSUME_NONNULL_BEGIN


// 打印机基类
@interface LuckPrinter : LuckPrinterInfo <CBPeripheralDelegate>

#pragma mark - 基础功能

@property (nonatomic , strong) dispatch_queue_t queue;
@property (nonatomic , strong, nullable) CBPeripheral *peripheral;
@property (nonatomic , strong) CBCharacteristic *writeCht;
@property (nonatomic , strong) CBCharacteristic *writeWithoutRspCht;

@property (nonatomic , assign) NSUInteger credit;
@property (nonatomic , assign) NSUInteger mtu;
@property (nullable , nonatomic , strong) NSMutableArray *imageList;
@property (nonatomic , assign) NSUInteger index;


@property (nonatomic , assign) BOOL isLabel;
@property (nonatomic , copy)TaskCompelete errorCompelete;


/// 发送任务
/// - Parameter task: 根据任务发送
- (void)sendTask:(LPSendTask *)task;

// 多态， 根据不一样的peripheral返回不同型号的设备（子类）
+ (nullable LuckPrinter *)printerWithPeripheral:(CBPeripheral *)peripheral;

#pragma mark - interface




/// 同步属性到打印机
- (void)synchronizeToPrinterCompelete:(void(^)(void))compelete;

/// 获取打印机信息
/// - Parameter callback: 回调
- (void)getPrinterInfo:(nullable void(^)(LuckPrinterInfo *info, NSError *error))callback;


/// 升级固件， 会先查询状态
/// - Parameters:
///   - versionData: 固件
///   - callback: 回调
- (void)updateVersion:(NSData *)versionData callback:(nullable void(^)(NSError *error))callback;


/// 打印标签，会先查询状态
/// - Parameters:
///   - images: 图片列表
///   - copies: 份数
///   - callback: 回调
- (void)printLabelImages:(NSArray <UIImage *>*)images copies:(NSUInteger)copies callback:(nullable void(^)(NSError *error))callback;

/// 打印非标签， 会先查询状态
/// - Parameters:
///   - images: 图片列表
///   - copies: 份数
///   - callback: 回调
- (void)printImages:(NSArray <UIImage *>*)images copies:(NSUInteger)copies callback:(nullable void(^)(NSError *error))callback;


/// 缩放到打印机使用的尺寸，前提必选当前有连接设备，注意如果是标签打印，请先设置isLabel为YES
/// - Parameter image: 要缩放的图片
- (UIImage *)normalPreviewImage:(UIImage *)image;

/// 缩放切二值化
/// - Parameter image: 要处理的图片
- (UIImage *)ezPreviewImage:(UIImage *)image;

/// 缩放切抖动
/// - Parameter image: 要处理的图片
- (UIImage *)ddPreviewImage:(UIImage *)image;

// 以下为内部集成用
- (void)bqSendImageLoopCompelete:(TaskCompelete)compelete;
- (void)jzSendImageLoopCompelete:(TaskCompelete)compelete;
- (void)zdSendImageLoopCompelete:(TaskCompelete)compelete;

- (void)getInfoCompelete:(TaskCompelete)compelete;

@end

NS_ASSUME_NONNULL_END
