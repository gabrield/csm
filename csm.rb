require 'sinatra'
require 'coffee-script'


get '/' do
  erb :index
end

get '/js/coffee/:file.js'  do |file|
  coffee file.to_sym
end



