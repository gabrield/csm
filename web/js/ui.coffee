class MainWindowView extends Backbone.View
    initialize: ->
        $(@el).sortable(placeholder: "ui-state-highlight").disableSelection()

class CameraView extends Backbone.View
    initialize: ->
        $(@el)
        

$(document).ready ->
    main_window = new MainWindowView el: $ '#main-window'
    camera_view = new CameraView el: $ '#camera-view'