require 'sinatra'
require 'coffee-script'
require 'base64'
require "./videoencoder"

get '/' do
  erb :index
end

get '/js/coffee/:file.js'  do |file|
  coffee file.to_sym
end

post '/:session_id/save/' do
  session_id = params[:session_id]
  
  begin
    FileUtils.mkdir(session_id)
  rescue
    content = params[:file]
    image_id = params[:image_id]

    content = content.gsub 'data:image/png;base64,', ''
    image_data = Base64.decode64 content

    File.open("#{session_id}/img#{image_id}.png", 'wb') { |file| file.write image_data }
  end 
  200
end

post '/:session_id/finished/' do
  video = VideoEncoder.new "#{params[:session_id]}", "#{params[:session_id]}/#{params[:session_id]}.avi"  
  video.encode
  200
end

get '/:session_id/is_video_ready/' do |session_id|
   is_video_ready = File.exist? "#{session_id}/#{session_id}.avi"
   
   return 'true' if is_video_ready
   'false'
end

get '/:session_id/download/' do
  send_file "#{params[:session_id]}/#{params[:session_id]}.avi", :filename => "#{params[:session_id]}.avi", :type => 'Video/avi'
end

