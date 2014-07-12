#include "bench.h"

static omxcam_yuv_planes_t planes;
static uint32_t current;
static uint32_t current_frames;
static uint32_t frame_size;
static int total_frames;
static int bg_error = 0;
static int quit = 0;

static void on_data_video (uint8_t* buffer, uint32_t length){
  current += length;
  
  if (current == frame_size){
    current = 0;
    
    if (++current_frames == total_frames){
      bg_error = omxcam_video_stop ();
    }
  }
}

static void on_data_video_async (uint8_t* buffer, uint32_t length){
  current += length;
  
  if (current == frame_size){
    current = 0;
    
    if (++current_frames == total_frames){
      quit = 1;
      bg_error = omxcam_video_stop_async ();
    }
  }
}

static void on_data_still (uint8_t* buffer, uint32_t length){
  //No-op
}

int yuv_video (bench_t* req){
  current = 0;
  current_frames = 0;
  
  omxcam_video_settings_t settings;
  
  omxcam_video_init (&settings);
  settings.on_ready = req->on_ready;
  settings.on_data = on_data_video;
  settings.on_stop = req->on_stop;
  settings.format = OMXCAM_FORMAT_YUV420;
  settings.camera.width = req->width;
  settings.camera.height = req->height;
  
  omxcam_yuv_planes (req->width, req->height, &planes);
  
  frame_size = planes.offset_v + planes.length_v;
  total_frames = req->frames;
  
  int error = omxcam_video_start (&settings, OMXCAM_CAPTURE_FOREVER);
  
  return error ? error : bg_error;
}

int yuv_video_async (bench_t* req){
  current = 0;
  current_frames = 0;
  
  omxcam_video_settings_t settings;
  
  omxcam_video_init (&settings);
  settings.on_ready = req->on_ready;
  settings.on_data = on_data_video_async;
  settings.on_stop = req->on_stop;
  settings.format = OMXCAM_FORMAT_YUV420;
  settings.camera.width = req->width;
  settings.camera.height = req->height;
  
  omxcam_yuv_planes (req->width, req->height, &planes);
  
  frame_size = planes.offset_v + planes.length_v;
  total_frames = req->frames;
  
  if (omxcam_video_start_async (&settings)) return -1;
  
  while (!quit){
    if (omxcam_video_read_async ()) return -1;
  }
  
  return bg_error;
}

int yuv_still (bench_t* req){
  omxcam_still_settings_t settings;
  
  omxcam_still_init (&settings);
  settings.on_ready = req->on_ready;
  settings.on_data = on_data_still;
  settings.on_stop = req->on_stop;
  settings.format = OMXCAM_FORMAT_YUV420;
  settings.camera.width = req->width;
  settings.camera.height = req->height;
  
  return omxcam_still_start (&settings);
}