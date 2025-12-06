module ar_math
    use iso_c_binding
contains

function ar_mix(a, b, t) result(out) bind(C, name="ar_mix")
    real(c_float), value :: a, b, t
    real(c_float) :: out
    out = a + (b - a) * t
end function ar_mix

subroutine ar_rotate(px, py, angle, rx, ry) bind(C, name="ar_rotate")
    use iso_c_binding
    real(c_float), value :: px, py, angle
    real(c_float), intent(out) :: rx, ry
    real(c_float) :: c, s
    c = cos(angle)
    s = sin(angle)
    rx = px * c - py * s
    ry = px * s + py * c
end subroutine ar_rotate

end module ar_math
