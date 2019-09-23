module BranchResolver(
    input [2:0] branch,
    input zero,
    input sign,
    output reg branchTaken
);

always @(*)
begin
    case (branch)
        3'd0:   branchTaken = 1'd0;
        3'd1:   branchTaken = zero;
        3'd2:   branchTaken = ~zero;
        3'd3:   branchTaken = ~sign | zero;
        3'd4:   branchTaken = ~sign & ~zero;
        3'd5:   branchTaken = sign | zero;
        3'd6:   branchTaken = sign;
        default:    branchTaken = 1'd0; 
    endcase
end

endmodule