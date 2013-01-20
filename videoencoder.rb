class VideoEncoder

@_imglist
@ffmpeg_cmd = "ffmpeg"
@ffmpeg_params
@outfile

  def initilize(outputfile)
    @_imglist = Array.new
    @outfile = outputfile
  end

  def encode()
      
  end

  def addimg(img)
    @_imglist.push img
  end

  def rmimg(img)
    @_imglist.delete img
  end

end
