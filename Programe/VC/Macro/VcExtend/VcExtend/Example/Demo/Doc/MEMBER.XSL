<?xml version="1.0" encoding="gb2312"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html"/>

<xsl:param name="ClassName"/>
<xsl:param name="MemberName"/>

<xsl:template match="/">
    <xsl:apply-templates select="doc/class[@name=$ClassName]">
    </xsl:apply-templates>
</xsl:template>

<xsl:template match="class">
    <xsl:apply-templates select="function[@name=$MemberName]">
    </xsl:apply-templates>
</xsl:template>

<xsl:template match="function">
<table width="640" align="center" class="10pt">

<tr>
<td height="20">
</td>
</tr>

<tr>
<td class="18pt">
<xsl:value-of select="$ClassName"/>::<xsl:value-of select="@name" />
</td>
</tr>

<tr>
<td height="5">
</td>
</tr>

<tr class="12pt">
<td>
<b><xsl:value-of select="access" /></b>&#160;<xsl:value-of select="prototype" disable-output-escaping="yes"/>
</td>
</tr>

<tr>
<td height="10">
</td>
</tr>

<tr>
<td class="10ptb" height="32">
��&#160;&#160;��
</td>
</tr>

<tr>
<td>
<xsl:value-of select="����" disable-output-escaping="yes"/>
</td>
</tr>

<xsl:if test="����">

<tr>
<td height="20">
</td>
</tr>

<tr>
<td class="10ptb" height="32">
����ֵ
</td>
</tr>

<tr>
<td>
[<xsl:value-of select="����/type" />]&#160;<xsl:value-of select="����/����" disable-output-escaping="yes"/>
</td>
</tr>

</xsl:if>

<xsl:if test="����">

<tr>
<td height="10">
</td>
</tr>

<tr>
<td class="10ptb" height="32">
��&#160;&#160;��
</td>
</tr>

<xsl:for-each select="����">

<tr>
<td height="40">
<b><xsl:value-of select="@name" /></b>
<br/>&#160;&#160;&#160;&#160;[<xsl:value-of select="type" />]&#160;<xsl:value-of select="����" disable-output-escaping="yes"/>
</td>
</tr>

</xsl:for-each>

</xsl:if>


<xsl:if test="˵��">

<tr>
<td height="10">
</td>
</tr>

<tr>
<td class="10ptb" height="32">
˵&#160;&#160;��
</td>
</tr>
<tr>
<td>
<xsl:value-of select="˵��" disable-output-escaping="yes"/>
</td>
</tr>

</xsl:if>

<tr>
<td height="40">
</td>
</tr>

</table>
</xsl:template>


<xsl:template match="class">
    <xsl:apply-templates select="function[@name=$MemberName]">
    </xsl:apply-templates>
<table width="640" align="center">
<tr>
<td height="20">

<a href="javascript:changePage('memberlist.xsl','','');">��Ա�б�</a> 
-
<xsl:element name="a">
<xsl:attribute name="href">
javascript:changePage('class.xsl','<xsl:value-of select="@name" />','')
</xsl:attribute>
<xsl:value-of select="@name" />�����</xsl:element>
-
<a href="javascript:changePage('classlist.xsl','','');">Home</a>
-
<a href="javascript:changePage('member.xsl','','');">ˢ��</a>
</td>
</tr>
</table>
</xsl:template>


</xsl:stylesheet>