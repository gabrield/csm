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
	file = params[:file]
	image_id = params[:image_id]

    img = Base64.decode64(file) 
    img_file = File.new("img" + image_id + ".png");
    img_file.write(img)
    img_file.close

end



