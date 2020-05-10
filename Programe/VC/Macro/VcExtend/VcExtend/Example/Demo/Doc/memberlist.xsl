<?xml version="1.0" encoding="gb2312"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html"/>

<xsl:param name="ClassName"/>
<xsl:param name="MemberName"/>

<xsl:template match="/">
    <xsl:apply-templates select="doc/class[@name=$ClassName]" />
</xsl:template>

<xsl:template match="doc/class">
<table width="640" align="center" class="10pt">

<tr>
<td height="20">
</td>
</tr>

<tr>
<td class="18pt">
<xsl:value-of select="@name" /> 成员列表 
</td>
</tr>

<tr>
<td height="10">
</td>
</tr>

<tr><td>
<table border="1" cellpadding="5" cols="2" frame="below" rules="rows" class="10pt">
<xsl:for-each select="function">

        <tr>			
	    <td width="20%">
            <xsl:if test="分类">
	    <br/>
	    <DIV class="10ptb"><xsl:value-of select="分类" /></DIV>
	    <br/>

            </xsl:if>
	    <xsl:element name="a">
            <xsl:attribute name="href">
	    javascript:changePage('member.xsl','','<xsl:value-of select="@name"/>')
	    </xsl:attribute> 
	    <xsl:value-of select="@name" />
            </xsl:element>
	    </td>
	    <td width="80%">
            <xsl:if test="分类">
	    <br/>
	    <DIV class="10ptb">&#160;</DIV>
	    <br/>

            </xsl:if>
            <xsl:value-of select="简述" disable-output-escaping="yes" />
	    </td>
	</tr>
</xsl:for-each>
</table>
</td></tr>

<tr>
<td height="40">
</td>
</tr>

<tr>
<td height="20" class="12pt">

<xsl:element name="a">
<xsl:attribute name="href">
javascript:changePage('class.xsl','<xsl:value-of select="@name" />','')
</xsl:attribute>
<xsl:value-of select="@name" />类概述</xsl:element>
-
<xsl:if test="BaseCort='obj'">
<xsl:element name="a">
<xsl:attribute name="href">
javascript:changePage('memberlist.xsl','<xsl:value-of select="base"/>','')
</xsl:attribute> 
基类成员列表</xsl:element>
-
</xsl:if>
<xsl:if test="BaseCort='mfcCustom'">
<xsl:element name="a">
<xsl:attribute name="href">
javascript:changePage('memberlist.xsl','<xsl:value-of select="base"/>','')
</xsl:attribute> 
基类成员列表</xsl:element>
-
</xsl:if>
<a href="javascript:changePage('classlist.xsl','','');">Home</a>
-
<a href="javascript:changePage('memberlist.xsl','','');">刷新</a>
</td>
</tr>

</table>
</xsl:template>

</xsl:stylesheet>