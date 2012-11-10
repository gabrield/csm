class Uploader
    save_images:(images,callback) ->
        image_id = 0
        _.each images, (image) =>
            image_id += 1
            $.post '/save/',
                file: $(image).attr 'src'
                image_id: image_id,
            
        callback()
    
    finished: ->
        $.post '/finished/'
        
$(document).ready ->
    window.uploader = new Uploader