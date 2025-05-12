# Video Processing Statistics

## Performance Summary

### Camera Processing (Real-time)
| Metric               | Value          |
|----------------------|----------------|
| Total processing time| 31.2145 seconds|
| Total frames         | 630            |
| Display FPS          | 20.18          |
| Processing FPS       | 26.86          |

### Video File Processing
| Video File    | Frames | Time (s) | FPS  |
|--------------|--------|----------|------|
| video1.mp4   | 274    | 28.39    | 9.65 |
| video2.mp4   | 256    | 24.10    | 10.62|
| video3.mp4   | 267    | 20.40    | 13.09|
| video4.mp4   | 375    | 31.36    | 11.96|
| video5.mp4   | 629    | 30.52    | 20.61|
| video6.mp4   | 419    | 12.63    | 33.19|
| video7.mp4   | 198    | 21.32    | 9.29 |
| video8.mp4   | 594    | 34.04    | 17.45|
| video9.mp4   | 192    | 9.37     | 20.49|
| video10.mp4  | 453    | 46.05    | 9.84 |

## Key Metrics

- **Best file performance:** video6.mp4 (33.19 FPS)
- **Worst performance:** video7.mp4 (9.29 FPS) 
- **Average FPS (files):** 15.70
- **Average FPS (camera display):** 20.18

## Technical Details

- **Processing path:** 
  - Files: C:/Users/avpap/source/repos/FotoTrapC/FotoTrapC/datas/
  - Camera: Device 0 (built-in)
- **Detection method:** Haar Cascade (frontalcatface_extended.xml)
- **Processing parameters:**
  - Scale factor: 1.1
  - Min neighbors: 3
  - Min object size: 30x30 px
- **Build configuration:**
  - OpenCV 4.x
  - C++20
  - CMake 3.8+