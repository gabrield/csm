require 'open3'

class VideoEncoder

@_imglist
@ffmpeg_cmd
@ffmpeg_prms
@outfile

  def initialize(outputfile)
    @_imglist    = Array.new
    @outfile     = outputfile
    @ffmpeg_cmd  = "ffmpeg"
    @ffmpeg_prms = " -f image2 -i img%d.png -sameq -y " + @outfile
  end

  def encode()
    ffmpeg = Thread.new do
      p @ffmpeg_cmd, @ffmpeg_prms, @outfile
      system @ffmpeg_cmd + @ffmpeg_prms
    end
    ffmpeg.join
  end

  def addimg(img)
    @_imglist.push img
  end

  def rmimg(img)
    @_imglist.delete img
  end

end
