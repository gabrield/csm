require 'sinatra'


get '/' do
  erb :index
end


get '/coffee/'  do
  coffee :index
end



