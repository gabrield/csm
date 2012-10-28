class MainWindowView extends Backbone.View
    initialize: ->
        @$el.sortable(items: "li:not(.toolbar)", placeholder: "ui-state-highlight").disableSelection()
        @$el.bind 'sortupdate', (event, ui) ->
            window.camera_view.trigger('render') unless _.any( $(ui.item[0]).parents('li'), (el) -> $(el).is('.toolbar'))
        
class ToolbarView extends Backbone.View
    events: 
        'click button#shot': 'shot'
        'click button#save': 'save'
    
    initialize: ->
        @$el.find('button').button()
        
    shot: ->
        window.last_frame_view.trigger('render')
        
    save: ->
        $('#saving-dialog').dialog
            title: 'Saving'
            modal: yes
        
class CameraView extends Backbone.View
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
                
class LastFrameView extends Backbone.View
    initialize: ->
        @camera = window.camera_view
        @bind 'render', @render
        
    render: -> 
        canvas = @camera.canvas[0]
        video = @camera.video[0]
        
        context = canvas.getContext '2d'
        context.drawImage video, 0, 0, 320/2, 240/2
        
        image = @$el.find('img')
        image.attr 'src', canvas.toDataURL 'image/webp 1'
        window.framebar_view.addFrame image
        
class FramebarView extends Backbone.View
    render: ->
        @$el.find('ul').sortable(placeholder: "ui-state-highlight").disableSelection()
        @$el.animate scrollTop: @$el.find('img:last').offset().top, 'slow'
    
    addFrame: ($image) ->
        html = $image[0].outerHTML
        @$el.find('ul').append "<li>#{html}</li>"
        @render()
              
$(document).ready ->
    if not ('webkitGetUserMedia' of navigator or 'getUserMedia' of navigator)
        $('#old-browser-dialog').dialog
            title: 'Update your browser'
            modal: yes
            buttons:
              ok: -> document.location.href = 'http://google.com/chrome'
    else
      new MainWindowView el: $ '#main-window'
      new ToolbarView el: $ '#toolbar-view'
      window.camera_view = new CameraView el: $ '#camera-view'
      window.last_frame_view = new LastFrameView el: $ '#last-frame-view'
      window.framebar_view = new FramebarView el: $ '#framebar-view'
    
    