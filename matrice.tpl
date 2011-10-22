        <table id="matrice_table">
            %i=0
            %for line in lines:
            %j=0
            <tr>
                %for c in line:
                    <td class="
                        %if c=='0':
                            no_cell
                        %else:
                            has_cell
                        %end
                        " x='{{j}}' y='{{i}}'>
                    </td>
                %j+=1
                %end
            </tr>
            %i+=1
            %end
        </table>
%rebase base
