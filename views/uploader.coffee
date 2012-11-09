class Uploader extends Backbone.Model
    url: '/save/'
    addImages:(images) ->
        image_id = 0
        _.each images, (image) =>
            image_id += 1
            $.post '/save/',
                file: $(image).attr 'src'
                image_id: image_id
        
        
$(document).ready ->
    window.uploader = new Uploader