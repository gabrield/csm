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

  s_id = params[:session_id]
  
  begin
    FileUtils.mkdir(s_id)
  ensure
    content = params[:file]
    image_id = params[:image_id]

    content = content.gsub 'data:image/png;base64,', ''
    image_data = Base64.decode64 content

    File.open("#{s_id}/img#{image_id}.png", 'wb') { |file| file.write image_data }
  end 
  200
end

post '/:session_id/finished/' do
  video = VideoEncoder.new "#{params[:session_id]}", "#{params[:session_id]}/#{params[:session_id]}.avi"  
  video.encode
  200
end

get '/:session_id/is_video_ready' do
    

get '/:session_id/download/' do
  send_file "#{params[:session_id]}/#{params[:session_id]}.avi", :filename => "#{params[:session_id]}.avi", :type => 'Video/avi'
end

