<?xml version="1.0" encoding="gb2312"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html"/>

<xsl:param name="ClassName"/>
<xsl:param name="MemberName"/>

<xsl:template match="/">
    <xsl:apply-templates select="doc" />
</xsl:template>

<xsl:template match="doc">

<div align="center">
  <center>
      <table border="1" cellpadding="5" cols="2" frame="below" rules="rows" width="640">
    <tr>
      <td height="60" align="center">
      <b>
      <font size="6" color="navy"><xsl:value-of select="ProjectName" /></font>
      <font size="5" color="navy">代码文档</font>
      </b>
      </td>
    </tr>
  </table>
  </center>
</div>
<div align="center">
  <center>
    <table border="1" cellpadding="5" cols="2" frame="below" rules="rows" width="640" class="10pt">
 
    <xsl:for-each select="class">
    <xsl:sort select="@name" />
        <tr>			
	    <td width="20">
	    <xsl:element name="a">
            <xsl:attribute name="href">
	    javascript:changePage('class.xsl','<xsl:value-of select="@name"/>','')
	    </xsl:attribute> 
	    <b><xsl:value-of select="@name" /></b>
            </xsl:element>
	    </td>
	    <td width="80%">
                <xsl:value-of select="简述"  disable-output-escaping="yes"/>
	    </td>
	</tr>
    </xsl:for-each>

    </table>
  </center>
</div>
</xsl:template>

</xsl:stylesheet>