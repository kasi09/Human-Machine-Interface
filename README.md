# Human-Machine-Interface
HMI implemented with Myo Armband in Visual C++

this repository includes the main files from a Visual C++ project

MyForm.h/cpp:
- EMG and IMU data collection from Myo Armband
- Feature Extraction (mean absolute value, waveform length, zero crossing, slope sign change)
- Classifiers (Linear Discriminant Analysis, Support Vector Machine)
- Plots raw and feature data
- Supports hand gesture training and recognition

Device.h: controls Myo device(s)
