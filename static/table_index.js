$(document).ready(function (){
    $("td").click(function (){
        if ($(this).hasClass('no_cell')){
            $(this).removeClass('no_cell').addClass('has_cell');
        } else {
            $(this).removeClass('has_cell').addClass('no_cell');
        }
        var ajax_url="/change_state/"+$(this).attr('x')+'/'+$(this).attr('y');
        $.ajax(ajax_url);
    });
});
