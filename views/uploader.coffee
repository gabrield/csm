class Uploader extends Backbone.Model
    url: '/save/'
    addImages:(images) ->
        _.each images, (image) =>
            @set 'file', $(image).attr 'src'
            @save()
        
        
$(document).ready ->
    window.uploader = new Uploader