uniform sampler2D texture;  // The texture of the sprite
uniform vec4 outlineColour;  // The color of the outline
uniform float outlineThickness;  // The thickness of the outline

void main()
{
    vec2 texSize = textureSize(texture, 0);
    vec2 texCoord = gl_TexCoord[0].xy;

    // Offsets for sampling neighboring pixels
    vec2 offsetX = vec2(outlineThickness / texSize.x, 0.0);
    vec2 offsetY = vec2(0.0, outlineThickness / texSize.y);

    // Sample surrounding pixels
    float alpha = texture2D(texture, texCoord).a;
    float alphaLeft = texture2D(texture, texCoord - offsetX).a;
    float alphaRight = texture2D(texture, texCoord + offsetX).a;
    float alphaUp = texture2D(texture, texCoord + offsetY).a;
    float alphaDown = texture2D(texture, texCoord - offsetY).a;

    // Determine if pixel is at an edge
    if (alpha == 0.0 && (alphaLeft > 0.0 || alphaRight > 0.0 || alphaUp > 0.0 || alphaDown > 0.0)) {
        gl_FragColor = outlineColour; // Draw the outline
    } else {
        gl_FragColor = texture2D(texture, texCoord); // Keep original color
    }
}
