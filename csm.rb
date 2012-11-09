require 'sinatra'
require 'coffee-script'
require 'base64'


get '/' do
  erb :index
end

get '/js/coffee/:file.js'  do |file|
  coffee file.to_sym
end

post '/save/' do
	content = params[:file]
	image_id = params[:image_id]

    content = content.gsub 'data:image/png;base64,', ''
    img = Base64.decode64(content)


    File.open("img" + image_id + ".png", 'wb') { |file| file.write(img) }
end



