local matmul = {}

function matmul.matmul(A, B)
    local s = 0.0
    local NI = #A
    local NK = #B 
    local NJ = #B[1]
    for k = 1, NK do
        local Bk = B[k]
        for i = 1, NI do
            local Ai = A[i]
            for j = 1, NJ do
                s = s + Ai[k] * Bk[j]
                --s = s + A[i][k] * B[k][j]
            end
        end
    end
    return s
end

return matmul
