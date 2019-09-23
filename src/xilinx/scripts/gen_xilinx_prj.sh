#!/bin/bash
if [ x"$1" == "x" ]; then
    echo "Please specify the verilog source folder"
    exit 1
fi
HDL_SRC_DIR=$1

echo '<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
<project xmlns="http://www.xilinx.com/XMLSchema" xmlns:xil_pn="http://www.xilinx.com/XMLSchema">
  <header>
  </header>
  <version xil_pn:ise_version="14.7" xil_pn:schema_version="2"/>
  <files>'

id=1
# CPU files
for vfile in $(ls $HDL_SRC_DIR/cpu/*.v); do
    echo "    <file xil_pn:name=\"$vfile\" xil_pn:type=\"FILE_VERILOG\">"
    echo "        <association xil_pn:name=\"BehavioralSimulation\" xil_pn:seqID=\"$id\"/>"
    echo "        <association xil_pn:name=\"Implementation\" xil_pn:seqID=\"$id\"/>"
    echo "    </file>"
    id=$((id+1))
done

# VGA files
for vfile in $(ls $HDL_SRC_DIR/vga/*.v); do
    echo "    <file xil_pn:name=\"$vfile\" xil_pn:type=\"FILE_VERILOG\">"
    echo "        <association xil_pn:name=\"BehavioralSimulation\" xil_pn:seqID=\"$id\"/>"
    echo "        <association xil_pn:name=\"Implementation\" xil_pn:seqID=\"$id\"/>"
    echo "    </file>"
    id=$((id+1))
done

# Include files
for vfile in $(ls $HDL_SRC_DIR/cpu/*.vh); do
    echo "    <file xil_pn:name=\"$vfile\" xil_pn:type=\"FILE_VERILOG\">"
    echo "        <association xil_pn:name=\"Implementation\" xil_pn:seqID=\"$id\" xil_pn:seqIDinc=\"$id\"/>"
    echo "    </file>"
    id=$((id+1))
done

echo '    <file xil_pn:name="../MIPS32SOC_pins.ucf" xil_pn:type="FILE_UCF">'
echo "        <association xil_pn:name=\"Implementation\" xil_pn:seqID=\"$id\"/>"
echo '    </file>
</files>
  <autoManagedFiles>
  </autoManagedFiles>
  <properties>
    <property xil_pn:name="Create Binary Configuration File" xil_pn:value="true" xil_pn:valueState="non-default"/>
    <property xil_pn:name="Create Bit File" xil_pn:value="true" xil_pn:valueState="default"/>
    <property xil_pn:name="Device Family" xil_pn:value="Spartan6" xil_pn:valueState="non-default"/>
    <property xil_pn:name="Device" xil_pn:value="xc6slx9" xil_pn:valueState="non-default"/>
    <property xil_pn:name="Package" xil_pn:value="csg324" xil_pn:valueState="non-default"/>
    <property xil_pn:name="Implementation Top" xil_pn:value="MIPS32SOC" xil_pn:valueState="non-default"/>'
echo "    <property xil_pn:name=\"Implementation Top File\" xil_pn:value=\"$HDL_SRC_DIR/cpu/MIPS32SOC.v\" xil_pn:valueState=\"non-default\"/>"
echo '    <property xil_pn:name="Implementation Top Instance Path" xil_pn:value="/MIPS32SOC" xil_pn:valueState="non-default"/>
    <property xil_pn:name="Working Directory" xil_pn:value="." xil_pn:valueState="non-default"/>
    <property xil_pn:name="Auto Implementation Compile Order" xil_pn:value="false" xil_pn:valueState="non-default"/>
    <property xil_pn:name="Manual Implementation Compile Order" xil_pn:value="true" xil_pn:valueState="non-default"/>
  </properties>
  <bindings/>
  <libraries/>
</project>'