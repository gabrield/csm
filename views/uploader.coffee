class Uploader extends Backbone.Model
    url: '/save/'
    addImages:(images) ->
        image_id = 0
        _.each images, (image) =>
            image_id += 1
            @set 'file', $(image).attr 'src'
            @set 'image_id', image_id
            @save()
        
        
$(document).ready ->
    window.uploader = new Uploader