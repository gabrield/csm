class Uploader
    save_images:(images,callback) ->
        image_id = 0
        _.each images, (image) =>
            image_id += 1
            $.post "/#{window.session_id()}/save/",
                file: $(image).attr 'src'
                image_id: image_id,
            
        callback()
    
    finished: ->
        $.post "/#{window.session_id()}/finished/"
        
$(document).ready ->
    window.session_id = ->
        session_id = 'xxxxxxxxx'.replace /[x]/g , ->
            _.random 9
        
        window.session_id = ->
            session_id
        
        session_id
        
    window.uploader = new Uploader