require 'sinatra'
require 'coffee-script'


get '/' do
  erb :index
end

# to render the coffee script to the main page
get '/coffee/'  do
  coffee :ui
end



