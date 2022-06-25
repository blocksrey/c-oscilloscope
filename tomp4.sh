cd output
ffmpeg -y -framerate 60 -i %05d.ppm -c:v libx264 -pix_fmt yuv420p -crf 13 output.mp4
