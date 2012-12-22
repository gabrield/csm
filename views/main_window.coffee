class Zoom
    current: 1
    allowed: [0.4, 0.5, 0.65, 0.75, 0.9, 1, 1.2, 1.3, 1.5, 1.75, 1.8, 2]
    
    can_zoom_in: -> @current isnt _.last @allowed
    can_zoom_out: -> @current isnt _.first @allowed
    
    current_index: ->
        @allowed.indexOf(@current)
    
    in: ->
        @zoom @allowed[@current_index()+1] if @can_zoom_in()
        
    out: ->
        @zoom @allowed[@current_index()-1] if @can_zoom_out()
        
    zoom: (factor) ->
        @current = factor
        $('.zoomable').css zoom: factor

class window.MainWindowView extends Backbone.View
    zoom: new Zoom

    initialize: ->
        @$el.sortable(items: "li:not(.toolbar)", placeholder: "ui-state-highlight").disableSelection()
        @$el.bind 'sortupdate', (event, ui) ->
            window.camera_view.trigger('render') unless _.any( $(ui.item[0]).parents('li'), (el) -> $(el).is('.toolbar'))
            
