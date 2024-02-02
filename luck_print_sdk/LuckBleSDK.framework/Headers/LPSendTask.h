//
//  LPSendTask.h
//  LuckBleSDK
//
//  Created by junky on 2023/11/1.
//

#import <UIKit/UIKit.h>
#import <LuckBleSDK/LuckPrinterInfo.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^TaskCompelete)( NSObject * _Nullable obj);
typedef NSObject * _Nullable(^TaskParse)(NSData *data);

@interface LPSendTask : NSObject

@property (nonatomic , readonly) NSString *uuid;
@property (nonatomic , readonly) NSData *data;
@property (nullable , nonatomic , readonly) TaskCompelete compelete;
@property (nonatomic , readonly) TaskParse parse;
@property (nonatomic , readonly) NSUInteger timeout;


+ (instancetype)getStateTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)getInfoTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)getThickTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)getTimeTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)getModelTaskCompelete:(TaskCompelete)compelete;

+ (instancetype)setThickTask:(NSUInteger)thick compelete:(TaskCompelete)compelete;
+ (instancetype)l2SetThickTask:(NSUInteger)thick compelete:(TaskCompelete)compelete;
+ (instancetype)setTimeTask:(NSUInteger)time compelete:(TaskCompelete)compelete;
+ (instancetype)setPaperTask:(LPPaperType)type compelete:(TaskCompelete)compelete;
+ (instancetype)l2SetPaperTask:(LPPaperType)type compelete:(TaskCompelete)compelete;


+ (instancetype)d2SetPaperWidthTask:(NSUInteger)type compelete:(TaskCompelete)compelete;

+ (instancetype)printerEnableTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)p15PrinterEnableTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)printerWakeTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)printerStopTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)hll1printerStopTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)y50PprinterStopTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)printerEnterPaperTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)printerOutPaperTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)printerLocationTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)l2PrinterLocationTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)printerWalkTask:(NSUInteger)walk compelete:(TaskCompelete)compelete;
+ (instancetype)printerSendImageTask:(UIImage *)image compelete:(TaskCompelete)compelete;
+ (instancetype)a4PrinterSendImageTask:(UIImage *)image compelete:(TaskCompelete)compelete;
+ (instancetype)a46PrintrtGetSpeedTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)a46PrinterSetSpeedTask:(NSUInteger)speed compelete:(TaskCompelete)compelete;


#pragma mark - 面单
+ (instancetype)mdGetStateTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)mdGetSnTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)mdGetVersionTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)mdGetModelTaskCompelete:(TaskCompelete)compelete;

+ (instancetype)mdCreatePageTask:(NSUInteger)width height:(NSUInteger)height compelete:(TaskCompelete)compelete;
+ (instancetype)mdGapTask:(NSUInteger)m n:(NSUInteger)n compelete:(TaskCompelete)compelete;
+ (instancetype)mdClearTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)mdSetSpeedTask:(NSUInteger)speed compelete:(TaskCompelete)compelete;
+ (instancetype)mdSetThickTask:(NSUInteger)thick compelete:(TaskCompelete)compelete;
+ (instancetype)mdSetCopiesTask:(NSUInteger)copies compelete:(TaskCompelete)compelete;
+ (instancetype)mdPrintImageTask:(UIImage *)image compelete:(TaskCompelete)compelete;
+ (instancetype)mdPrintImage2Task:(UIImage *)image compelete:(TaskCompelete)compelete;




#pragma mark - parse

+ (NSUInteger)otaCreditWithData:(NSData *)data;
+ (NSUInteger)mtuWithData:(NSData *)data;
+ (NSUInteger)creditWithData:(NSData *)data;


#pragma mark - OTA

+ (instancetype)otaStartTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)otaSearchTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)otaCleanTask:(NSData *)data compelete:(TaskCompelete)compelete;
+ (instancetype)otaResetTaskCompelete:(TaskCompelete)compelete;
+ (instancetype)otaSendTask:(NSData *)data loc:(NSUInteger)loc compelete:(TaskCompelete)compelete;






#pragma mark - test

+ (instancetype)timeoutTask;


@end

NS_ASSUME_NONNULL_END
