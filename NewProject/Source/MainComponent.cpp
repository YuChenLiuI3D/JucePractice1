/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

class DragAndDropDemo : public Component,
	public DragAndDropContainer
{
public:
	DragAndDropDemo()
		: sourceListBox("D+D source", nullptr)
	{
		setName("Drag-and-Drop");

		sourceListBox.setModel(&sourceModel);
		sourceListBox.setMultipleSelectionEnabled(true);

		addAndMakeVisible(sourceListBox);
	}

	void resized() override
	{
		Rectangle<int> r(getLocalBounds().reduced(8));

		sourceListBox.setBounds(r.withSize(250, 180));
	}

private:
	//==============================================================================
	struct SourceItemListboxContents : public ListBoxModel
	{
		// The following methods implement the necessary virtual functions from ListBoxModel,
		// telling the listbox how many rows there are, painting them, etc.
		int getNumRows() override
		{
			return 30;
		}

		void paintListBoxItem(int rowNumber, Graphics& g,
			int width, int height, bool rowIsSelected) override
		{
			if (rowIsSelected)
				g.fillAll(Colours::lightblue);

			g.setColour(Colours::black);
			g.setFont(height * 0.7f);

			g.drawText("Draggable Thing #" + String(rowNumber + 1),
				5, 0, width, height,
				Justification::centredLeft, true);
		}

		var getDragSourceDescription(const SparseSet<int>& selectedRows) override
		{
			// for our drag description, we'll just make a comma-separated list of the selected row
			// numbers - this will be picked up by the drag target and displayed in its box.
			StringArray rows;

			for (int i = 0; i < selectedRows.size(); ++i)
				rows.add(String(selectedRows[i] + 1));

			return rows.joinIntoString(", ");
		}
	};

	//==============================================================================
	ListBox sourceListBox;
	SourceItemListboxContents sourceModel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DragAndDropDemo)
};

//==============================================================================
MainContentComponent::MainContentComponent()
{
	addAndMakeVisible(myLabel = new Label(String(),"Hello World!"));
	myLabel->setFont(Font(40.00f, Font::bold));
	myLabel->setJustificationType(Justification::topLeft);
	myLabel->setEditable(false, false, false);
	myLabel->setColour(Label::textColourId, Colours::black);
	myLabel->setColour(TextEditor::textColourId, Colours::black);
	myLabel->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(changeLabelButton = new TextButton(String()));
	changeLabelButton->setButtonText("Press to change label text");
	changeLabelButton->addListener(this);

	addAndMakeVisible(addListBoxButton = new TextButton(String()));
	addListBoxButton->setButtonText("Press to add item to listbox");
	addListBoxButton->addListener(this);


    setSize (600, 400);
}

MainContentComponent::~MainContentComponent()
{
	myLabel = nullptr;
	changeLabelButton = nullptr;
	addListBoxButton = nullptr;
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0x88888888));
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
	myLabel->setBounds(60, 60, 296, 48);
	changeLabelButton->setBounds(350, 120, 200, 32);
	addListBoxButton->setBounds(350, 320, 200, 32);
}

void MainContentComponent::buttonClicked(Button * buttonThatWasClicked)
{
	if (buttonThatWasClicked == changeLabelButton)
	{
		AlertWindow changeLabelWindow("Change label text.", "Please enter a text to change label:", AlertWindow::QuestionIcon);
		changeLabelWindow.addTextEditor("textForLabel", "Hello World!", "text field:");
		changeLabelWindow.addButton("OK", 1, KeyPress(KeyPress::returnKey, 0, 0));
		String textUserEnterForLabel;
		if (changeLabelWindow.runModalLoop() != 0) // is they picked 'ok'
		{
			textUserEnterForLabel = changeLabelWindow.getTextEditorContents("textForLabel");
		}
		myLabel->setText(textUserEnterForLabel,NotificationType::sendNotification);
	}

	if (buttonThatWasClicked == addListBoxButton)
	{
		AlertWindow addTextBoxWindow("Add item to ListBox.", "Please enter a text to add an item to ListBox:", AlertWindow::QuestionIcon);
		addTextBoxWindow.addTextEditor("textForListBox", "", "text field:");
		addTextBoxWindow.addButton("OK", 1, KeyPress(KeyPress::returnKey, 0, 0));
		String textUserEnterForListBox;
		if (addTextBoxWindow.runModalLoop() != 0) // is they picked 'ok'
		{
			textUserEnterForListBox = addTextBoxWindow.getTextEditorContents("textForListBox");
		}
	}
}
