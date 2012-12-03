require 'sinatra'
require 'coffee-script'
require 'base64'

get '/' do
  erb :index
end

get '/js/coffee/:file.js'  do |file|
  coffee file.to_sym
end

post '/:session_id/save/' do
  content = params[:file]
  image_id = params[:image_id]

  content = content.gsub 'data:image/png;base64,', ''
  image_data = Base64.decode64 content

  File.open("img#{image_id}.png", 'wb') { |file| file.write image_data }
    
  200
end

post '/:session_id/finished/' do
    200
end

