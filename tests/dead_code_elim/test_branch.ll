define i32 @test(i32 %x) {
entry:
  br i1 true, label %then, label %else

then:
  %a = add i32 %x, 1
  br label %exit

else:
  %b = add i32 %x, 99
  br label %exit

exit:
  %result = phi i32 [ %a, %then ], [ %b, %else ]
  ret i32 %result
}
