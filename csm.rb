require 'sinatra'
require 'coffee-script'


get '/' do
  erb :index
end


get '/coffee/'  do
  coffee :ui
end



