<!DOCTYPE html>
<html lang='en'>
    <head>
        <title>Game Of Life Web</title>
        <meta charset="utf-8"/>
        <style type='text/css'>
            table { border: 0px collapse; }
            tr { height:10px; }
            td { width:10px; }
            .no_cell {background:#FFF}
            .has_cell {background:#000}
        </style>
    </head>
    <body>
        <table>
            %for line in lines:
            <tr>
                %for c in line:
                    <td class="
                        %if c=='0':
                            no_cell
                        %else:
                            has_cell
                        %end
                    ">
                    </td>
                %end
            </tr>
            %end
        </table>
    </body>
</html>

