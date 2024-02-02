#
# Be sure to run `pod lib lint luck_print_sdk.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'luck_print_sdk'
  s.version          = '0.1.0'
  s.summary          = 'A short description of luck_print_sdk.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/LuckJingle-XM/luck_print_sdk'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Junky' => '921969987@qq.com' }
  s.source           = { :git => 'https://github.com/LuckJingle-XM/luck_print_sdk.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '13.0'
  
  # s.resource_bundles = {
  #   'luck_print_sdk' => ['luck_print_sdk/Assets/*.png']
  # }
  s.vendored_frameworks = "luck_print_sdk/*.framework"
#  s.source_files = "luck_print_sdk/*.framework"
  # s.frameworks = 'UIKit', 'MapKit'
  # s.dependency 'AFNetworking', '~> 2.3'
end
