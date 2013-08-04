class CSM.CameraView extends Backbone.View
    initialize: ->
        @canvas = @$el.find('canvas')
        @video = @$el.find('video')
        @bind 'render', @render
        @render()
        
    render: ->
        navigator.webkitGetUserMedia {video: true},
            (stream) =>
                stream = window.webkitURL.createObjectURL stream
                @video.attr('src', stream)
           ,(exception) ->
                console.log exception
