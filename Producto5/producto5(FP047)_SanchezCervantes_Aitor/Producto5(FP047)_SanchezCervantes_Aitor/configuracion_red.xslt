<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html" encoding="UTF-8" indent="yes"/>
    <!-- Template principal -->
    <xsl:template match="/">
        <html>
            <head>
                <title>Configuracion de Red</title>
                <style>
                    table {
                        width: 50%;
                        margin: 20px auto;
                        border-collapse: collapse;
                    }
                    th, td {
                        border: 1px solid #000;
                        padding: 8px;
                        text-align: left;
                    }
                    th {
                        background-color: #f2f2f2;
                        font-size: 1.2em;
                        text-transform: uppercase;
                    }
                    tr:nth-child(even) {
                        background-color: #f9f9f9;
                    }
                    td:first-child {
                        font-weight: bold;
                    }
                </style>
            </head>
            <body>
                <h2>Configuracion de Red</h2>
                <table>
                    <tr>
                        <th>Elemento</th>
                        <th>Valor</th>
                    </tr>
                    <tr>
                        <td>IP</td>
                        <td><xsl:value-of select="ConfiguracionRed/IP"/></td>
                    </tr>
                    <tr>
                        <td>MascaraSubred</td>
                        <td><xsl:value-of select="ConfiguracionRed/MascaraSubred"/></td>
                    </tr>
                    <tr>
                        <td>PuertaEnlace</td>
                        <td><xsl:value-of select="ConfiguracionRed/PuertaEnlace"/></td>
                    </tr>
                    <tr>
                        <td>DNS</td>
                        <td><xsl:value-of select="ConfiguracionRed/DNS"/></td>
                    </tr>
                    <tr>
                        <td>VelocidadMedia</td>
                        <td><xsl:value-of select="ConfiguracionRed/VelocidadMedia"/></td>
                    </tr>
                    <tr>
                        <td>NumeroSaltos</td>
                        <td><xsl:value-of select="ConfiguracionRed/NumeroSaltos"/></td>
                    </tr>
                    <tr>
                        <td>Saltos</td>
                        <td>
                            <xsl:for-each select="ConfiguracionRed/Saltos/Salto">
                                <xsl:value-of select="."/><br/>
                            </xsl:for-each>
                        </td>
                    </tr>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>
