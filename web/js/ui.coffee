class MainWindowView extends Backbone.View
    initialize: ->
        @$el.sortable(placeholder: "ui-state-highlight").disableSelection()

class CameraView extends Backbone.View
    initialize: (options) ->
        @opts = options
        @render()
        
    render: ->
        navigator.webkitGetUserMedia 'video',
            (stream) =>
                stream = window.webkitURL.createObjectURL stream
                @$el.find('video').attr('src', stream)
           ,(exception) ->
                console.log exception
        
$(document).ready ->
    main_window = new MainWindowView el: $ '#main-window'
    main_window.camera_view = new CameraView {el: $('#camera-view'), main_window: main_window }
    