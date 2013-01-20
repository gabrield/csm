class VideoEncoder

@_imglist
@ffmpeg_cmd = "ffmpeg"
@ffmpeg_params = "-y -f image2 -i img%d.png -sameq"
@outfile

  def initialize(outputfile)
    @_imglist = Array.new
    @outfile = outputfile
  end

  def encode()
    ffmpeg = Thread.new do
      IO.popen([@_ffmpeg_cmd, @ffmpeg_params, @outfile])
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
