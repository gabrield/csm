class CSM.ToolbarView extends Backbone.View
    events: 
        'click button#zoomin': 'zoomin'
        'click button#zoomout': 'zoomout'
        'click button#shot': 'shot'
        'click button#save': 'save'
        'click button#finished': 'finished'
        'click button#preview': 'preview'
    
    initialize: ->
        @$el.find('button').button()
        
    shot: ->
        CSM.last_frame_view.trigger('render')
        
    save: ->
        dialog = $('#saving-dialog').dialog
            title: 'Saving'
            modal: yes
            
        CSM.uploader.save_images =>
            dialog.remove()
            
    finished: ->
        CSM.uploader.finished()
        $('#finished-dialog').dialog
            title: 'Saving'
            modal: yes
            
    preview: ->
        CSM.last_frame_view.preview()
        
    zoomin: ->
        CSM.main_window_view.zoom.in()
        
    zoomout: ->
        CSM.main_window_view.zoom.out()
