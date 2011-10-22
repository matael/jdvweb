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
%rebase base
