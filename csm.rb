require 'sinatra'
require 'coffee-script'


get '/' do
  erb :index
end

get '/coffee/'  do
  # to render the coffee script to the main page
  coffee :ui
end



