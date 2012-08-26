class MainWindowView extends Backbone.View
    initialize: ->
        @$el.sortable(placeholder: "ui-state-highlight").disableSelection()
        @$el.bind 'sortupdate', ->
            window.camera_view.trigger('render')
        
class ToolbarView extends Backbone.View
    events: 
        'click button#shot': 'shot'
    
    initialize: ->
        @$el.find('button').button()
        
    shot: ->
        window.last_frame_view.trigger('render')
        
class CameraView extends Backbone.View
    initialize: ->
        @canvas = @$el.find('canvas')
        @video = @$el.find('video')
        @bind 'render', @render
        @render()
        
    render: ->
        navigator.webkitGetUserMedia 'video',
            (stream) =>
                stream = window.webkitURL.createObjectURL stream
                @video.attr('src', stream)
           ,(exception) ->
                console.log exception
                
class LastFrameView extends Backbone.View
    initialize: (options) ->
        @camera = window.camera_view
        @bind 'render', @render
        
    render: -> 
        canvas = @camera.canvas[0]
        video = @camera.video[0]
        context = canvas.getContext '2d'
        context.drawImage video, 0, 0
        @$el.find('img').attr 'src', canvas.toDataURL 'image/webp'
    
              
$(document).ready ->
    new MainWindowView el: $ '#main-window'
    new ToolbarView el: $ '#toolbar-view'
    window.camera_view = new CameraView el: $ '#camera-view'
    window.last_frame_view = new LastFrameView el: $ '#last-frame-view'
    