
Pod::Spec.new do |s|

  s.name         = "SabineSwissSDK"
  s.version      = "1.0.2"
  s.summary      = "SDK for communicate Sabine Bluetooth Devices."
  s.description  = <<-DESC
First release at 20170821, see more from: http://www.sabinetek.com/l,6,0.html#license 
                   DESC

  s.homepage     = "http://www.sabinetek.com/l,6,0.html#solution"

  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author       = { "zhaoxinlei" => "zhaoxinlei@sabinetek.com" }
  s.platform     = :ios, "8.0"

  s.source       = { :git => "https://github.com/Zeta-XL/SabineSwissSDK.git", :tag => "#{s.version}" }
  s.vendored_frameworks = "SabineSwissSDK.framework"
  s.frameworks = "ExternalAccessory", "AVFoundation", "AudioToolbox"

  s.requires_arc = true
end
