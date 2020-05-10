<?xml version="1.0" encoding="gb2312"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html"/>

<xsl:param name="ClassName"/>
<xsl:param name="MemberName"/>

<xsl:template match="/">
    <xsl:apply-templates select="doc/class[@name=$ClassName]">
    </xsl:apply-templates>
</xsl:template>

<xsl:template match="doc/class">

<table width="640" align="center" class="10pt">

<tr>
<td height="20">
</td>
</tr>

<tr>
<td class="18pt">
<xsl:value-of select="@name" />
</td>
</tr>

<tr>
<td>
<hr size="1" color="red" />
</td>
</tr>

<tr>
<td height="20">
</td>
</tr>

<tr>
<td>
<xsl:value-of select="简述" disable-output-escaping="yes" />
</td>
</tr>

<tr>
<td height="20">
</td>
</tr>

<tr>
<td>
<xsl:value-of select="说明" disable-output-escaping="yes" />
</td>
</tr>

<tr>
<td height="40">
</td>
</tr>

<tr>
<td height="20">
基类：<xsl:value-of select="base" />
</td>
</tr>

<tr>
<td height="10">
</td>
</tr>

<tr>
<td height="20">
<b>#include &quot;<xsl:value-of select="file" />.h&quot;</b>
</td>
</tr>

<tr>
<td height="40">
</td>
</tr>

<tr class="12pt">
<td height="20">
<a href="javascript:changePage('memberlist.xsl','','');">成员列表</a> 
-
<xsl:if test="BaseCort='obj'">
<xsl:element name="a">
<xsl:attribute name="href">
javascript:changePage('class.xsl','<xsl:value-of select="base"/>','')
</xsl:attribute> 
基类</xsl:element>
-
</xsl:if>
<xsl:if test="BaseCort='mfcCustom'">
<xsl:element name="a">
<xsl:attribute name="href">
javascript:changePage('class.xsl','<xsl:value-of select="base"/>','')
</xsl:attribute> 
基类</xsl:element>
-
</xsl:if>
<a href="javascript:changePage('classlist.xsl','','');">Home</a>
-
<a href="javascript:changePage('class.xsl','','');">刷新</a>
</td>
</tr>

</table>
</xsl:template>

</xsl:stylesheet>