class MainWindowView extends Backbone.View
    initialize: ->
        @$el.sortable(items: "li:not(.toolbar)", placeholder: "ui-state-highlight").disableSelection()
        @$el.bind 'sortupdate', (event, ui) ->
            window.camera_view.trigger('render') unless _.any( $(ui.item[0]).parents('li'), (el) -> $(el).is('.toolbar'))
        
class ToolbarView extends Backbone.View
    events: 
        'click button#shot': 'shot'
        'click button#save': 'save'
        'click button#finished': 'finished'
        'click button#preview': 'preview'
    
    initialize: ->
        @$el.find('button').button()
        
    shot: ->
        window.last_frame_view.trigger('render')
        
    save: ->
        dialog = $('#saving-dialog').dialog
            title: 'Saving'
            modal: yes
            
        window.uploader.save_images $('img'), =>
            dialog.remove()
            
    finished: ->
        window.uploader.finished()
        $('#finished-dialog').dialog
            title: 'Saving'
            modal: yes
            
    preview: ->
        window.last_frame_view.preview()
        
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
        @image = @$el.find 'img'
        
    render: -> 
        canvas = @camera.canvas[0]
        video = @camera.video[0]

        canvas.width = video.videoWidth
        canvas.height = video.videoHeight
        
        context = canvas.getContext '2d'
        context.drawImage video, 0, 0
        @image.attr 'src', canvas.toDataURL 'image/webp 1'
        window.framebar_view.add_frame @image
        
    preview: ->
        first_frame = window.framebar_view.get_first_frame()
        @show_frame first_frame
        if (first_frame.has_next())
            @timer_show first_frame.next()
        
    timer_show: (frame) ->
        setTimeout =>
            @show_frame frame
            if (frame.has_next())
                @timer_show frame.next()
        , 1000/25
        
    show_frame: (frame) ->
        @image.attr 'src', frame.src

class EmptyFrame
    constructor: ->
        true
        
    from_image: ($image) ->
        @src = $image.attr 'src'
        
    has_next: ->
        no
    
    next: ->
        off
    
    notify_of_sibling: (sibling) ->
        @has_next = ->
            yes
            
        @next = ->
            sibling
            
    set_el: (el) ->
        @$el =$(el)
        @bind_events()
        
    bind_events: ->
        @$el.on 'click', =>
            @click()
        
    render: ->
        "<img src='#{@src}'>"
        
    click: ->
        window.last_frame_view.show_frame this
        
        
class FramebarView extends Backbone.View
    frames: []

    render: ->
        @$el.find('ul').sortable(placeholder: "ui-state-highlight").disableSelection()
        @$el.animate scrollTop: @$el.find('img:last').offset().top, 'slow'
    
    add_frame: ($image) ->
        new_frame = new window.EmptyFrame()
        new_frame.from_image $image
        
        if not (_.isEmpty @frames)
            _.last(@frames).notify_of_sibling new_frame
        
        new_frame.set_el $("<li>#{new_frame.render()}</li>").appendTo @$el.find('ul')
        
        @frames.push new_frame
        @render()
        
    get_first_frame: ->
        _.first @frames
              
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
      window.EmptyFrame = EmptyFrame
      window.framebar_view = new FramebarView el: $ '#framebar-view'
    
    