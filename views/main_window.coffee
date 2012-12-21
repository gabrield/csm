class window.MainWindowView extends Backbone.View
    initialize: ->
        @$el.sortable(items: "li:not(.toolbar)", placeholder: "ui-state-highlight").disableSelection()
        @$el.bind 'sortupdate', (event, ui) ->
            window.camera_view.trigger('render') unless _.any( $(ui.item[0]).parents('li'), (el) -> $(el).is('.toolbar'))